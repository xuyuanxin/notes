
/* 32-bit ELF base types. */
typedef __u32	Elf32_Addr;
typedef __u16	Elf32_Half;
typedef __u32	Elf32_Off;
typedef __s32	Elf32_Sword;
typedef __u32	Elf32_Word;

/* 64-bit ELF base types. */
typedef __u64	Elf64_Addr;
typedef __u16	Elf64_Half;
typedef __s16	Elf64_SHalf;
typedef __u64	Elf64_Off;
typedef __s32	Elf64_Sword;
typedef __u32	Elf64_Word;
typedef __u64	Elf64_Xword;
typedef __s64	Elf64_Sxword;

/*
    +---
    | 


*/



#define EI_NIDENT	16
/*-----------------------------------------------------------------------------------
@e_ident
    e_ident[EI_MAG0] == ELFMAG0
    e_ident[EI_MAG1] == ELFMAG1
    e_ident[EI_MAG2] == ELFMAG2
    e_ident[EI_MAG3] == ELFMAG3
    e_ident[EI_CLASS] == ELFCLASS32 
    e_ident[EI_DATA] ==  ELFDATA2LSB 
    e_ident[EI_VERSION] == EV_CURRENT
    e_ident[7~] == unused
@e_type  ET_REL
    This member identifies the object file type.
@e_machine 
    This member's value specifies the required architecture for an individual file.
@e_version EV_CURRENT
    This member identifies the object file version.
@e_shoff @e_shnum @e_shentsize
    The ELF header's  @e_shoff member gives the byte offset from the beginning of the 
    file to the section header table; @e_shnum tells how many entries the section he-
    ader table contains; @e_shentsize gives the size in bytes of each entry.
@e_shstrndx 
    This member holds the section header table index of the entry associated with the 
    section name string table. If the file has no section name string table, this me-
    mber holds the value SHN_UNDEF. 
-----------------------------------------------------------------------------------*/
typedef struct elf32_hdr{
  unsigned char	e_ident[EI_NIDENT];
  Elf32_Half	e_type;
  Elf32_Half	e_machine;
  Elf32_Word	e_version;
  Elf32_Addr	e_entry;  /* Entry point */
  Elf32_Off	    e_phoff;
  Elf32_Off	    e_shoff;
  Elf32_Word	e_flags;
  Elf32_Half	e_ehsize;
  Elf32_Half	e_phentsize;
  Elf32_Half	e_phnum;
  Elf32_Half	e_shentsize;
  Elf32_Half	e_shnum;
  Elf32_Half	e_shstrndx; /* Section header string table index */
} Elf32_Ehdr;

/*----------------------------------------------------------------------------------- 
@EI_PAD
    This value marks the beginning of the unused bytes in e_ident. These bytes are r-
    eserved and set to zero; 
-----------------------------------------------------------------------------------*/
#define	EI_MAG0		0		/* e_ident[] indexes */
#define	EI_MAG1		1
#define	EI_MAG2		2
#define	EI_MAG3		3
#define	EI_CLASS	4
#define	EI_DATA		5
#define	EI_VERSION	6
#define	EI_OSABI	7
#define	EI_PAD		8 

/* e_ident[EI_MAG0 ~ EI_MAG3] */
#define	ELFMAG0		0x7f		/* EI_MAG */
#define	ELFMAG1		'E'         /* 0x45 */
#define	ELFMAG2		'L'         /* 0x4c */
#define	ELFMAG3		'F'         /* 0x46 */
#define	ELFMAG		"\177ELF"
#define	SELFMAG		4

/* e_ident[EI_CLASS]  */
#define	ELFCLASSNONE	0		/* EI_CLASS Invalid class*/
#define	ELFCLASS32	1 /* 32-bit objects */
#define	ELFCLASS64	2 /* 64-bit objects */
#define	ELFCLASSNUM	3

/* e_ident[EI_DATA] */
#define ELFDATANONE	0 /* Invalid data encoding*/
#define ELFDATA2LSB	1
#define ELFDATA2MSB	2

/* e_version, EI_VERSION */
#define EV_NONE		0		
#define EV_CURRENT	1
#define EV_NUM		2

/* These constants define the different elf file types */
#define ET_NONE   0 /**/ /* No file type */
#define ET_REL    1 /* Relocatable file */
#define ET_EXEC   2 /* Executable file */
#define ET_DYN    3 /* Shared object file */
#define ET_CORE   4 /* Core file */
#define ET_LOPROC 0xff00 /* Processor-specific */
#define ET_HIPROC 0xffff /* Processor-specific */

/* e_version, EI_VERSION */
#define EV_NONE		0	/* Invalid version */	
#define EV_CURRENT	1   /* Current version */
#define EV_NUM		2

/*---------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------
section header table
    An object file's section header table lets one locate all the file's sections. T-
    he section header table is an array of  Elf32_Shdr structures as described below. 
    A section header table index is a subscript into this array. The ELF header's 
    @e_shoff member gives the byte offset from the beginning of the file to the sect-
    ion header table; @e_shnum tells how many entries the section header table conta-
    ins; @e_shentsize gives the size in bytes of each entry.

@sh_name 
    This member specifies the name of the section. Its value is an index into the se-
    ction header string table section (see "String Table" below), giving the location 
    of a null-terminated string.
@sh_type 
    This member categorizes the section's contents and semantics.
@sh_flags 
    Sections support 1-bit flags that describe miscellaneous attributes. 
@sh_link @sh_info
    Two members in the section header, @sh_link and @sh_info, hold special informati-
    on, depending on section type.

-----------------------------------------------------------------------------------*/
typedef struct {
  Elf32_Word	sh_name;
  Elf32_Word	sh_type;
  Elf32_Word	sh_flags;
  Elf32_Addr	sh_addr;
  Elf32_Off     sh_offset;
  Elf32_Word	sh_size;
  Elf32_Word	sh_link;
  Elf32_Word	sh_info;
  Elf32_Word	sh_addralign;
  Elf32_Word	sh_entsize;
} Elf32_Shdr;

/* Special Sections

.shstrtab 
    This section holds section names.
.strtab 
    This section holds strings, most commonly the strings that represent the names a-
    ssociated with symbol table entries. If the file has a loadable segment that includes the symbol string
table, the section¡¯s attributes will include the SHF_ALLOC bit; otherwise, that bit will be off.

*/


/*-----------------------------------------------------------------------------------
Some section header table indexes are reserved; an object file will not have sections 
for these special indexes.
-----------------------------------------------------------------------------------*/
#define SHN_UNDEF	0
#define SHN_LORESERVE	0xff00
#define SHN_LOPROC	0xff00
#define SHN_HIPROC	0xff1f
#define SHN_ABS		0xfff1
#define SHN_COMMON	0xfff2
#define SHN_HIRESERVE	0xffff

/*------------------------------- Elf32_Shdr @sh_type -------------------------------
@SHT_NULL 
    This value marks the section header as inactive; it does not have an associated -
    section. Other members of the section header have undefined values.
@SHT_PROGBITS 
    The section holds information defined by the program, whose format and meaning a-
    re determined solely by the program. .text .data etc.
@SHT_SYMTAB and @SHT_DYNSYM
    These sections hold a symbol table.

*/
#define SHT_NULL	0
#define SHT_PROGBITS	1
#define SHT_SYMTAB	2
#define SHT_STRTAB	3
#define SHT_RELA	4
#define SHT_HASH	5
#define SHT_DYNAMIC	6
#define SHT_NOTE	7
#define SHT_NOBITS	8
#define SHT_REL		9
#define SHT_SHLIB	10
#define SHT_DYNSYM	11
#define SHT_NUM		12
#define SHT_LOPROC	0x70000000
#define SHT_HIPROC	0x7fffffff
#define SHT_LOUSER	0x80000000
#define SHT_HIUSER	0xffffffff

/* Elf32_Shdr @sh_flags 
@SHF_WRITE 
    The section contains data that should be writable during process execution.
@SHF_ALLOC 
    The section occupies memory during process execution. Some control sections do n-
    ot reside in the memory image of an object file ; this attribute is off for those 
    sections.
*/
#define SHF_WRITE	0x1
#define SHF_ALLOC	0x2
#define SHF_EXECINSTR	0x4
#define SHF_MASKPROC	0xf0000000


/*-----------------------------------------------------------------------------------
String Table(.strtab), Section Header String Table(.shstrtab)
String table sections hold null-terminated character sequences, commonly called stri-
ngs. The object file uses these strings to represent symbol and section names. One r-
eferences a string as an index into the string table section. The first byte, which -
is index zero, is defined to hold a null character. Likewise, a string table's last -
byte is defined to hold a null character , ensuring null termination for all strings. 
A string whose index is zero specifies either no name or a null name, depending on t-
he context. An empty string table section is permitted; its section header's @sh_size 
member would contain zero. Non-zero indexes are invalid for an empty string table . A 
section header's @sh_name member holds an index into the  section header string table 
section, as designated by the @e_shstrndx member of the ELF header. The following fi-
gures show a string table with 25 bytes and the strings associated with various inde-
xes.


*/
