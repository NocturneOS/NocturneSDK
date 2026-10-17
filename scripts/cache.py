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

                data = {key: BuildCache.__default_cache_entry() for key in tools}

                json.dump(data, fd)

    @staticmethod
    def __default_cache_entry() -> dict[str, bool]:
        return {"built": False, "configured": False, "installed": False}

    def __mark_tool(self, tool: str, flag: str, value: bool = True):
        with open(self.cache_path, "r+") as fd:
            data = json.load(fd)

            fd.seek(0, os.SEEK_SET)

            if tool not in data:
                data[tool] = BuildCache.__default_cache_entry()

            data[tool][flag] = value

            json.dump(data, fd)

            fd.truncate()

    def reset_state(self, tool: str):
        self.__mark_tool(tool, "configured", False)
        self.__mark_tool(tool, "built", False)
        self.__mark_tool(tool, "installed", False)

    def mark_tool_as_configured(self, tool: str):
        self.__mark_tool(tool, "configured")

    def mark_tool_as_built(self, tool: str):
        self.__mark_tool(tool, "built")

    def mark_tool_as_installed(self, tool: str):
        self.__mark_tool(tool, "installed")

    def __check_config(self, tool: str, key: str, default: bool = False) -> bool:
        with open(self.cache_path, "r") as fd:
            data = json.load(fd)

            if data.get(tool) is None:
                return default

            return data[tool][key]

    def is_built(self, tool: str) -> bool:
        return self.__check_config(tool, "built")

    def is_configured(self, tool: str) -> bool:
        return self.__check_config(tool, "configured")

    def is_installed(self, tool: str) -> bool:
        return self.__check_config(tool, "installed")
