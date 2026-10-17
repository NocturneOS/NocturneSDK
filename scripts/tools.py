from dataclasses import dataclass, field


@dataclass
class Tool:
    url: str
    configure_flags: list[str] | None
    priority: int

    build_system: str = field(default="configure_make")

    source_dir: str | None = field(default=None)

    install_postfix: str | None = field(default=None)

    build_commands: list[list[str]] | None = field(default=None)
    install_commands: list[list[str]] | None = field(default=None)

    def __post_init__(self):
        if self.source_dir is None:
            self.source_dir = self.url.split("/")[-1]

    def is_local(self) -> bool:
        return not self.url.startswith("http")


TOOLS = {
    "binutils": Tool(
        url="https://github.com/NocturneOS/binutils-gdb",
        configure_flags=[
            "--target={IN_GNU_TARGET}",
            "--disable-gdb",
            "--disable-python",
            "--disable-gdbserver",
            "--disable-docs",
            "--disable-tests",
            "--disable-werror",
        ],
        priority=0,
    ),
    "gcc": Tool(
        url="https://github.com/NocturneOS/gcc",
        configure_flags=[
            "--target={IN_GNU_TARGET}",
            "--enable-languages=c",
            "--disable-libssp",
            "--disable-libquadmath",
            "--disable-tests",
            "--disable-bootstrap",
            "--disable-libstdcxx",
        ],
        priority=1,
    ),
    # TODO: Add SDK itself as a tool
    "sdk": Tool(
        url="{IN_SDK_SOURCE}",
        source_dir="sdk",
        build_system="cmake",
        configure_flags=[
            "-DCMAKE_TOOLCHAIN_FILE=nocturne{IN_TARGET_BITS}.cmake",
            "-DCMAKE_C_COMPILER_WORKS=1",
            "-DCMAKE_CXX_COMPILER_WORKS=1",
        ],
        install_postfix="{IN_GNU_TARGET}/sysroot/usr",
        priority=2,
    ),
    "binutils_sysroot": Tool(
        url="https://github.com/NocturneOS/binutils-gdb",
        source_dir="binutils-gdb",
        configure_flags=[
            "--target={IN_GNU_TARGET}",
            "--disable-gdb",
            "--disable-python",
            "--disable-gdbserver",
            "--disable-docs",
            "--disable-tests",
            "--disable-werror",
            "--with-build-sysroot={IN_PREFIX}/{IN_GNU_TARGET}/sysroot",
        ],
        priority=3,
    ),
    "gcc_sysroot": Tool(
        url="https://github.com/NocturneOS/gcc",
        source_dir="gcc",
        configure_flags=[
            "--target={IN_GNU_TARGET}",
            "--enable-languages={IN_GCC_LANGS}",
            "--disable-libssp",
            "--disable-nls",
            "--disable-gcov",
            "--disable-libquadmath",
            "--disable-tests",
            "--disable-bootstrap",
            "--disable-libstdcxx",
            "--without-headers",
            "--disable-shared",
            "--disable-multilib",
            # "--disable-libgcc",
            "--with-sysroot={IN_PREFIX}/{IN_GNU_TARGET}/sysroot",
        ],
        build_commands=[
            ["make", "-j", "{IN_JOBS}", "all-gcc"],
            ["make", "-j", "{IN_JOBS}", "all-target-libgcc"],
        ],
        install_commands=[
            ["make", "install-gcc"],
            ["make", "install-target-libgcc"],
        ],
        priority=4,
    ),
}

# These tools are not visible in the `--help` and can't be selected,
# because it's a required part of build
__HIDDEN_TOOLS = ["sdk"]

AVAILABLE_TOOLS = [tool for tool in TOOLS if tool not in __HIDDEN_TOOLS]
