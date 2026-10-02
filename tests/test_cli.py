"""Small integration checks for the NJBF loader and stack machine."""

from pathlib import Path
import struct
import subprocess
import sys


OP = {
    "halt": 0, "pushc": 1, "add": 2, "div": 5, "mod": 6,
    "wrint": 8, "wrchr": 10,
}


def instruction(name: str, immediate: int = 0) -> int:
    return (OP[name] << 24) | (immediate & 0x00FF_FFFF)


def write_program(path: Path, words: list[int], *, magic: bytes = b"NJBF") -> None:
    path.write_bytes(struct.pack("<4sIII", magic, 4, len(words), 0)
                     + struct.pack(f"<{len(words)}I", *words))


def run(executable: Path, program: Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run([executable, program], text=True, capture_output=True, check=False)


def require(condition: bool, message: str) -> None:
    if not condition:
        raise AssertionError(message)


def main() -> None:
    executable = Path(sys.argv[1])
    work = Path(sys.argv[2])
    work.mkdir(parents=True, exist_ok=True)

    answer = work / "answer.njbf"
    write_program(answer, [
        instruction("pushc", 40), instruction("pushc", 2), instruction("add"),
        instruction("wrint"), instruction("pushc", 10), instruction("wrchr"),
        instruction("halt"),
    ])
    result = run(executable, answer)
    require(result.returncode == 0, result.stderr)
    require("\n42\nNinja Virtual Machine stopped" in result.stdout, result.stdout)

    bad_magic = work / "bad-magic.njbf"
    write_program(bad_magic, [instruction("halt")], magic=b"NOPE")
    result = run(executable, bad_magic)
    require(result.returncode != 0 and "not a Ninja binary" in result.stderr, result.stderr)

    underflow = work / "underflow.njbf"
    write_program(underflow, [instruction("add"), instruction("halt")])
    result = run(executable, underflow)
    require(result.returncode != 0 and "stack underflow" in result.stderr, result.stderr)

    divide_by_zero = work / "divide-by-zero.njbf"
    write_program(divide_by_zero, [
        instruction("pushc", 3), instruction("pushc", 0),
        instruction("mod"), instruction("halt"),
    ])
    result = run(executable, divide_by_zero)
    require(result.returncode != 0 and "division by zero" in result.stderr, result.stderr)

    print("4 integration scenarios passed")


if __name__ == "__main__":
    main()
