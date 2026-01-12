ENTRY (_start)
SECTIONS
{
  . = 0x0000;
  .vector :
  {
    KEEP(*(SORT_NONE(.vector)))
	. = ALIGN(16);
  }
  .text : {
    *(.text)
    *(.text.*)
    *(.rodata)
    *(.rodata*)
    . = ALIGN(4);
    _shell_command_start = .;
    KEEP (*(shellCommand))
    _shell_command_end = .;
  }
  . = 0x7f00;
  .stack : {
    PROVIDE (_stack = .);
  }
  .data : {*(.data)}
  .bss : {*(.bss)}
}
