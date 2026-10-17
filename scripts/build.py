import os
import pathlib
import subprocess
import sys

from . import arguments, git, cache
from .tools import TOOLS

TOOLS_SOURCES_DIR = "thirdparty"


def ensure_packages_downloaded(args: arguments.BuildArguments):
    os.makedirs(TOOLS_SOURCES_DIR, exist_ok=True)
    os.chdir(TOOLS_SOURCES_DIR)

    for tool in args.tools:
        tool_desc = TOOLS.get(tool)

        if tool_desc is None:
            print(f"Error: unknown tool `{tool}`")
            sys.exit(1)

        if not tool_desc.is_local():
            if pathlib.Path(tool_desc.source_dir).exists():
                print(f"tool: {tool} is already downloaded")
                continue

            tool_url = tool_desc.url

            print(f"tool: Downloading {tool} -> {tool_url} into {tool_desc.source_dir}")

            git.clone(tool_url, shallow=True, output=tool_desc.source_dir)

    os.chdir("..")


# Replaces unresolved formats in URL for each tool.
def resolve_tools(args: arguments.BuildArguments):
    for tool in TOOLS:
        tool_desc = TOOLS[tool]

        flags = {"IN_SDK_SOURCE": args.sdk_source}

        tool_desc.url = tool_desc.url.format(**flags)


def begin(args: arguments.BuildArguments):
    real_prefix = os.path.abspath(args.prefix)

    orig_dir = os.getcwd()

    resolve_tools(args)

    ensure_packages_downloaded(args)

    if args.download_only:
        return

    if not pathlib.Path(args.build_dir).exists():
        print(
            f"note: Build directory (`{args.build_dir}`) doesn't exist, creating it..."
        )
        os.makedirs(args.build_dir)

    os.chdir(args.build_dir)

    # Start build

    binutils_targets = [target + "-nocturne" for target in args.targets]

    # Each target will have its own build directory
    build_dirs = [f"build-{target}" for target in args.targets]

    for [cur_dir, cur_target, raw_target_name] in zip(
        build_dirs, binutils_targets, args.targets
    ):
        os.makedirs(cur_dir, exist_ok=True)

        os.chdir(cur_dir)

        bcache = cache.BuildCache(".")

        # Sort tools by their priority to build SDK in right order
        tools = sorted(
            {
                tool: TOOLS[tool]
                for tool in [*args.tools, "sdk"]
                if TOOLS.get(tool) is not None
            },
            key=lambda x: TOOLS[x].priority,
        )

        for tool_name in tools:
            tool = TOOLS[tool_name]

            os.makedirs(tool_name, exist_ok=True)
            os.chdir(tool_name)

            if not bcache.is_configured(tool_name):
                print(f"{tool_name}: configuring")

                configure_env = os.environ.copy()
                configure_env["PATH"] = f"{args.prefix}/bin:{configure_env['PATH']}"

                flags = tool.configure_flags

                input_flags = {
                    "IN_GNU_TARGET": cur_target,
                    "IN_RAW_TARGET": raw_target_name,
                    "IN_GCC_LANGS": ",".join(args.gcc_langs),
                    "IN_SDK_SOURCE": args.sdk_source,
                    "IN_TARGET_BITS": 32 if raw_target_name == "i586" else 64,
                }

                formatted_flags = [flag.format(**input_flags) for flag in flags]

                if tool.build_system == "configure_make":
                    command = [
                        f"{orig_dir}/{TOOLS_SOURCES_DIR}/{tool_name}/configure",
                        *formatted_flags,
                        "--prefix",
                        real_prefix,
                    ]
                elif tool.build_system == "cmake":
                    if tool_name == "sdk":
                        src_path = tool.url
                    else:
                        src_path = f"{orig_dir}/{TOOLS_SOURCES_DIR}/{tool_name}"

                    command = [
                        "cmake",
                        "-S",
                        src_path,
                        "-B",
                        pathlib.Path().cwd().as_posix(),
                        *formatted_flags,
                    ]

                else:
                    raise Exception(f"Unknown build system: {tool.build_system}")

                print(f"Command: {command}")
                print(f"Env: {configure_env}")

                retcode = subprocess.call(command, env=configure_env)

                if retcode != 0:
                    raise Exception(f"Failed to configure {tool_name}")

                bcache.mark_tool_as_configured(tool_name)

            if not bcache.is_built(tool_name):
                print(f"{tool_name}: building")

                if tool.build_system == "configure_make":
                    command = ["make", "-j", str(args.jobs)]
                elif tool.build_system == "cmake":
                    command = ["cmake", "--build", ".", "-j", str(args.jobs)]

                retcode = subprocess.call(command)

                if retcode != 0:
                    raise Exception(f"Failed to build {tool_name}")

                bcache.mark_tool_as_built(tool_name)

            # The config might be updated, so check it again
            if bcache.is_built(tool_name):
                # If compiler is built, install it to prefix path.

                print(f"{tool_name}: installing")

                if tool.build_system == "configure_make":
                    command = [
                        "make",
                        "install-gcc" if tool_name == "gcc" else "install",
                    ]
                elif tool.build_system == "cmake":
                    command = ["cmake", "--install", ".", "--prefix", args.prefix]

                retcode = subprocess.call(command)

                if retcode != 0:
                    raise Exception(f"Failed to install {tool_name}")

            # TODO: Then use that compiler to build NocturneLibC and NocturneLibM

            # TODO: Rebuild the compiler with sysroot support

            os.chdir("..")

        os.chdir("..")

        print(cur_dir, cur_target)

    os.chdir(orig_dir)
