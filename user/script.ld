ENTRY(_start)
SECTIONS {
  . = 0x401000;
  .text : { *(.text) }
}