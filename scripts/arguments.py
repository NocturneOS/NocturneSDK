from dataclasses import dataclass


@dataclass
class BuildArguments:
    targets: list[str]
    tools: list[str]
    build_dir: str
    prefix: str
    jobs: int
    gcc_langs: list[str]

    download_only: bool
    no_install: bool

    sdk_source: str

    reconfigure: list[str]
    clean: list[str]
