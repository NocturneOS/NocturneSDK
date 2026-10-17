import subprocess


def clone(url: str, shallow: bool = False, output: str | None = None):
    cmdline = ["git", "clone"]

    if shallow:
        cmdline += ["--depth", "1", "--no-tags"]

    cmdline += ["-b", "nocturne"]

    cmdline += [url]

    if output is not None:
        cmdline += [output]

    subprocess.call(cmdline)
