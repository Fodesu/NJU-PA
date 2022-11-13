#include <proc.h>
#include <elf.h>
#include <fs.h>
#include <malloc.h>

#ifdef __LP64__
# define Elf_Ehdr Elf64_Ehdr
# define Elf_Off  Elf64_Off
# define Elf_Phdr Elf64_Phdr
#else
# define Elf_Ehdr Elf32_Ehdr
# define Elf_Off  Elf32_Off
# define Elf_Phdr Elf32_Phdr
#endif
// static Elf_Phdr ehdr;
size_t ramdisk_write(const void *buf, size_t offset, size_t len);
size_t ramdisk_read(void *buf, size_t offset, size_t len);

static uintptr_t loader(PCB *pcb, const char *filename) {
  #ifdef __LP64__
    printf("defined x86\n");
  #else 
    printf("defined riscv32\n");
  #endif
  int fd = fs_open(filename, 0, 0);
  
  Elf_Ehdr elf_header;

  fs_lseek(fd, 0, SEEK_SET);
  fs_read(fd, &elf_header, sizeof(elf_header));
  //根据小端法 0x7F E L F
  assert(*(uint32_t *)elf_header.e_ident == 0x464c457f);
  
  Elf_Off ph_offset = elf_header.e_phoff;
  uint32_t entry = elf_header.e_entry;
  int ph_num = elf_header.e_phnum;

  Log("phoffset = %d  entry = %p  phnum = %d", ph_offset, entry, ph_num);
  
  for (int i = 0; i < ph_num; ++i){
    Elf_Phdr phdr;
    printf("in loop %d\n", i);
    assert(fs_lseek(fd, ph_offset + i * sizeof(phdr), SEEK_SET) != -1);
    assert(fs_read(fd, &phdr, sizeof(phdr)) != -1);
    printf("p_type == %d\n", phdr.p_type);
    if(phdr.p_type != PT_LOAD) continue;

    printf("PT_LOAD IN %d\n", i); 
    printf("%d %d %d %d\n", phdr.p_offset, phdr.p_paddr, phdr.p_vaddr, phdr.p_type);
    void * virt_addr = (void *)phdr.p_vaddr;
    assert(virt_addr); // virt_addr == NULL
    Elf_Off offset = phdr.p_offset;
    uint32_t file_size = phdr.p_filesz;

    printf("offset = %p\n", &offset);
    assert(fs_lseek(fd, offset, SEEK_SET) != -1);
    printf("fs_lseek end\n"); 
    assert(fs_read(fd, virt_addr, file_size) != -1);
    printf("read end\n");
    memset(virt_addr + file_size, 0, 
      phdr.p_memsz - file_size);

    printf("%d\n", i);
  }
  return entry;
}

// static void read(int fd, void *buf, size_t offset, size_t len){
//   fs_lseek(fd, offset, SEEK_SET);
//   fs_read(fd, buf, len);
// }

// static uintptr_t loader(PCB *pcb, const char *filename) {
//   int fd = fs_open(filename, 0, 0);
  
//   Elf_Ehdr elf_header;
//   read(fd, &elf_header, 0, sizeof(elf_header));
//   //根据小端法 0x7F E L F
//   assert(*(uint32_t *)elf_header.e_ident == 0x464c457f);
  
//   Elf_Off program_header_offset = elf_header.e_phoff;
//   size_t headers_entry_size = elf_header.e_phentsize;
//   int headers_entry_num = elf_header.e_phnum;

//   for (int i = 0; i < headers_entry_num; ++i){
//     Elf_Phdr section_entry;
//     read(fd, &section_entry, 
//       i * headers_entry_size + program_header_offset, sizeof(Elf_Phdr));
//     void * virt_addr;
//     switch (section_entry.p_type) {
//     case PT_LOAD:
//       printf("PT_LOAD ing\n");
//       virt_addr = (void *)section_entry.p_vaddr; 
//       read(fd, virt_addr, section_entry.p_offset, section_entry.p_filesz);
//       printf("read ending\n");
//       memset(virt_addr + section_entry.p_filesz, 0, 
//         section_entry.p_memsz - section_entry.p_filesz);
//       break;
    
//     default:
//       break;
//     }

//   }
  
//   return elf_header.e_entry;
// }


void naive_uload(PCB *pcb, const char *filename) {
  uintptr_t entry = loader(pcb, filename);
  Log("Jump to entry = %p", entry);
  ((void(*)())entry) ();
}
