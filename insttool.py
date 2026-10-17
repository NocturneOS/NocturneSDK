#!/usr/bin/env python

import argparse
import multiprocessing
import pathlib

from scripts import arguments, build, tools

SUPPORTED_TARGETS = ["i586", "x86_64"]
SUPPORTED_TOOLS = ["binutils", "gcc"]
SUPPORTED_GCC_LANGUAGES = ["c", "c++", "rust"]
DEFAULT_BUILD_DIR = "sdk-build"


def main():
    parser = argparse.ArgumentParser(suggest_on_error=True)

    parser.add_argument(
        "--targets",
        "-t",
        help="Targets to build tools for",
        choices=SUPPORTED_TARGETS,
        nargs="+",
        type=str,
        default=SUPPORTED_TARGETS,
    )

    parser.add_argument(
        "--tools",
        "-l",
        help="Tools to be built",
        type=str,
        choices=tools.AVAILABLE_TOOLS,
        default=tools.AVAILABLE_TOOLS,
    )

    parser.add_argument(
        "--build_dir",
        "-b",
        help="Directory where tools are being built",
        type=str,
        default=DEFAULT_BUILD_DIR,
    )

    parser.add_argument(
        "--jobs",
        "-j",
        help="Specify core count to use when building tools",
        type=int,
        default=multiprocessing.cpu_count(),
    )

    parser.add_argument(
        "--gcc-langs",
        help="Specify languages GCC will support",
        type=str,
        choices=SUPPORTED_GCC_LANGUAGES,
        nargs="+",
        default=SUPPORTED_GCC_LANGUAGES,
    )

    parser.add_argument(
        "--download-only",
        help="Only execute a download stage, then exit.",
        action="store_true",
        default=False,
    )

    parser.add_argument(
        "--prefix", "-p", help="SDK installation path", required=True, type=str
    )

    args = parser.parse_args()

    build.begin(
        arguments.BuildArguments(
            targets=args.targets,
            tools=args.tools,
            build_dir=args.build_dir,
            prefix=pathlib.Path(args.prefix).absolute().as_posix(),
            jobs=args.jobs,
            gcc_langs=args.gcc_langs,
            download_only=args.download_only,
            sdk_source=pathlib.Path(__file__).absolute().parent,
        )
    )

    print(args)


if __name__ == "__main__":
    main()
