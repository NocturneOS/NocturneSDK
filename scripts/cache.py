import json
import os
import pathlib

from .tools import TOOLS


class BuildCache:
    def __init__(self, build_target_path: str):
        self.target_path = os.path.abspath(build_target_path)
        self.cache_path = f"{self.target_path}/.cache.json"

        if not pathlib.Path(self.cache_path).exists():
            with open(self.cache_path, "w") as fd:
                tools = list(TOOLS.keys())

                data = {key: {"built": False, "configured": False} for key in tools}

                json.dump(data, fd)

    def mark_tool_as_configured(self, tool: str):
        with open(self.cache_path, "r+") as fd:
            data = json.load(fd)

            fd.seek(0, os.SEEK_SET)

            data[tool]["configured"] = True

            json.dump(data, fd)

            fd.truncate()

    def mark_tool_as_built(self, tool: str):
        with open(self.cache_path, "r+") as fd:
            data = json.load(fd)

            fd.seek(0, os.SEEK_SET)

            data[tool]["built"] = True

            json.dump(data, fd)

            fd.truncate()

    def is_built(self, tool: str) -> bool:
        with open(self.cache_path, "r") as fd:
            data = json.load(fd)

            return data[tool]["built"]

    def is_configured(self, tool: str) -> bool:
        with open(self.cache_path, "r") as fd:
            data = json.load(fd)

            return data[tool]["configured"]
