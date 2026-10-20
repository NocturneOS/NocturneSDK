import re
import subprocess
from dataclasses import dataclass, field

from shutil import which

from . import log


@dataclass
class HostTool:
    name: str
    verspec: re.Pattern

    version_command: str = field(default="--version")


HOST_TOOLS = [
    HostTool(name="gcc", verspec=re.compile(r"^.* \(GCC\) (?P<version>\d+\.\d+\.\d+)")),
    HostTool(
        name="cmake", verspec=re.compile(r"^.* version (?P<version>\d+\.\d+\.\d+)")
    ),
    HostTool(name="make", verspec=re.compile(r"GNU Make (?P<version>\d+\.\d+\.\d+)")),
]


def check_tools() -> bool:
    for i in HOST_TOOLS:
        path = which(i.name)

        if path is None:
            log.error(f"{i.name} required host tool is not installed.")
            return False

        hdl = subprocess.Popen(
            [path, i.version_command], stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        retcode = hdl.wait()

        if retcode != 0:
            log.error(f"Running command: `{path} {i.version_command}` failed!")
            log.error("stdout:")
            log.error("\n".join(hdl.stderr.readlines()))

            return False

        verstr = b"\n".join(hdl.stdout.readlines()).decode("utf-8")

        ver = i.verspec.match(verstr)

        log.ok(f"Found {i.name}: {path} (version {ver.group('version')})")
