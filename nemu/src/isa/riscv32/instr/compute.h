#include<isa.h>
def_EHelper(lui) {
  printf("load the lui\n");
  printf("Run: %s = %x\n", paddtoname(ddest), id_src1->imm);
  rtl_li(s, ddest, id_src1->imm);
  printf("lui 后 ddest == %x\n", *ddest);
  printf("Ending def_EHelper: lui, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(add) {
  printf("load the add\n");
  printf("Run: %s = %s + %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_add(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: add, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}
def_EHelper(sub) {
  printf("load the sub\n");
  printf("Run: %s = %s - %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_sub(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: sub, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}
def_EHelper(mul) {
  printf("load the mul\n");
  printf("Run: %s = %s * %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_mulu_lo(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: mul, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(mulh) {
  printf("load the mulh\n");
  printf("Run: %s = %s * %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_muls_hi(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: mulh, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(mulhu) {
  printf("load the mulhu\n");
  printf("Run: %s = %s * %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_mulu_hi(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: mulhu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(mulhsu) {
  printf("load the mulhsu\n");
  printf("Run: %s = %s * %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_li(s, ddest, (int64_t)((uint64_t)(*dsrc1) * (uint64_t)(*dsrc2)) >> 32);
  printf("Ending def_EHelper: mulhsu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(div) {
  printf("load the div\n");
  printf("Run: %s = %s / %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_divs_q(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: div, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(rem) {
  printf("load the rem\n");
  rtl_divs_r(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: remu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(remu) {
  printf("load the remu\n");
  rtl_divu_r(s, ddest, dsrc1, dsrc2);
  printf("Ending def_EHelper: remu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(sltu) {
  printf("load the sltu\n");
  if(*dsrc1< *dsrc2) {
    printf("Run: %s < %s , %s = 1\n", paddtoname(dsrc1), paddtoname(dsrc2), paddtoname(ddest));
    rtl_li(s, ddest, 1);
  } else {
    printf("Run: %s >= %s , %s = 0\n", paddtoname(dsrc1), paddtoname(dsrc2), paddtoname(ddest));
    rtl_li(s, ddest, 0);
  }
  printf("Ending def_EHelper: sltu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(xor) {
  printf("load the xor\n");
  printf("Run: %s = %s ^ %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_li(s, ddest, (*dsrc1) ^ (*dsrc2));
  printf("Ending def_EHelper: xor, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
} 

def_EHelper(or) {
  printf("load the or\n");
  printf("Run: %s = %s | %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_li(s, ddest, (*dsrc1) | (*dsrc2));
  printf("Ending def_EHelper: or, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
} 
def_EHelper(sll) {
  printf("load the sll\n");
  printf("Run: %s = %s << (%s & (0x1f))\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2) );
  rtl_li(s, ddest, *dsrc1 << (*dsrc2 & (0x1f)));
  printf("Ending def_EHelper: sll, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(sra) {
  printf("load the sra\n");
  printf("Run: %s = %s >> (%s & (0x1f))\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2) );
  rtl_li(s, ddest, (sword_t)*dsrc1 >> (*dsrc2 & (0x1f)));
  printf("Ending def_EHelper: sra, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(srl) {
  printf("load the srl\n");
  printf("Run: %s = %s >> (%s & (0x1f))\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2) );
  rtl_li(s, ddest, *dsrc1 >> (*dsrc2 & (0x1f)));
  printf("Ending def_EHelper: srl, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(and) {
  printf("load the and\n");
  printf("Run: %s = %s & %s\n", paddtoname(ddest), paddtoname(dsrc1), paddtoname(dsrc2));
  rtl_li(s, ddest, (*dsrc1) & (*dsrc2));
  printf("Ending def_EHelper: and, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(slt) {
  printf("load the slt\n");
  rtl_li(s, ddest, (sword_t)*dsrc1 < (sword_t)*dsrc2);
  printf("Ending def_EHelper: slt, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

// def_EHelper(sltu) {
//   printf("load the slt\n");
//   rtl_li(s, ddest, (sword_t)*dsrc1 < (sword_t)*dsrc2);
//   printf("Ending def_EHelper: slt, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
//   isa_reg_display();
// }

def_EHelper(addi) {
  printf("load the addi\n");
  printf("Run: %s = %s + %d\n", paddtoname(ddest), paddtoname(dsrc1), id_src2->imm);
  rtl_mv(s, ddest, id_src1->preg);
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 2);
  rtl_addi(s, ddest, ddest, id_src2->imm);
  printf("Ending def_EHelper: addi, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(srai) {
  printf("load the srai\n");
  // printf("Run: %s = %s >> (%d & (0x1f))\n", paddtoname(ddest), paddtoname(dsrc1), id_src2->imm);
  rtl_li(s, ddest, ((sword_t)*dsrc1) >> (id_src2->imm & (0x3f)));
  printf("Ending def_EHelper: srai, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(andi) {
  printf("load the andi\n");
  printf("Run: %s = %s & %d\n", paddtoname(ddest), paddtoname(dsrc1), id_src2->imm);
  rtl_andi(s, ddest, dsrc1, id_src2->imm);
  printf("Ending def_EHelper: andi, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(slli) {
  printf("load the slli\n");
  printf("Run: %s = %s << (%d & (0x3f))\n", paddtoname(ddest), paddtoname(dsrc1), id_src2->imm);
  rtl_li(s, ddest, *dsrc1 << (id_src2->imm & (0x3f)));
  printf("Ending def_EHelper: slli, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(xori) {
  printf("load the xori\n");
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 2);
  printf("Run: %s = %s ^ %x\n", paddtoname(ddest), paddtoname(dsrc1), id_src2->imm);
  rtl_li(s, ddest, (*dsrc1) ^ (id_src2->imm));
  printf("Ending def_EHelper: xori, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(slti) {
  printf("load the slti\n");
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 2);
  if((sword_t) *dsrc1 < (sword_t)id_src2->imm) {
    printf("Run: %s < %d , %s = 1\n", paddtoname(dsrc1), id_src2->imm, paddtoname(ddest));
    rtl_li(s, ddest, 1);
  } else {
    printf("Run: %s >= %d , %s = 0\n", paddtoname(dsrc1), id_src2->imm, paddtoname(ddest));
    rtl_li(s, ddest, 0);
  }
  printf("Ending def_EHelper: sltiu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}
def_EHelper(sltiu) {
  printf("load the sltiu\n");
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 2);
  if(*dsrc1 < id_src2->imm) {
    printf("Run: %s < %d , %s = 1\n", paddtoname(dsrc1), id_src2->imm, paddtoname(ddest));
    rtl_li(s, ddest, 1);
  } else {
    printf("Run: %s >= %d , %s = 0\n", paddtoname(dsrc1), id_src2->imm, paddtoname(ddest));
    rtl_li(s, ddest, 0);
  }
  printf("Ending def_EHelper: sltiu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(srli) {
  printf("load the srli\n");
  printf("Run: >> %d\n", id_src1->imm & (0x3f));
  rtl_li(s, ddest, (*dsrc1) >> (id_src2->imm & (0x3f)));
  printf("Ending def_EHelper: srli, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(auipc) {
  printf("load the auipc\n");
  // printf("pc == %x\n", s->pc);
  // printf("auipc 前 ddest == %x\n", *ddest);
  rtl_sext(s, &id_src1->imm, &id_src1->imm, 4);
  printf("simm = %d  0x%08x\n", id_src1->imm, id_src1->imm);
  printf("Run: %s = pc(0x%08x) + %x\n", paddtoname(ddest), s->pc, id_src1->imm);
  rtl_addi(s, ddest, &s->pc, id_src1->imm);
  printf("auipc 后 ddest == %x\n", *ddest);
  printf("Ending def_EHelper: auipc, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(jal) {
  if(*ddest != 0) {
    printf("load the jal\n");
    printf("Run: %s = 0x%08x\n", paddtoname(ddest), s->pc + 4);
  } else printf("load the j\n");
  rtl_li(s, ddest, s->pc + 4);
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 4);
  printf("simm %d  %x\n",id_src2->imm, id_src2->imm);
  printf("Run: dnpc(0x%08x) = pc(0x%08x) + %x\n", s->dnpc, s->pc, id_src2->imm);
  rtl_addi(s, &s->dnpc, &s->pc, id_src2->imm);
  printf("Ending def_EHelper: jal, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(jalr) {
  printf("load the jalr\n");
  // printf("Run: %s = 0x%08x\n", paddtoname(ddest), s->pc + 4);
  rtl_li(s, ddest, s->pc + 4);
  rtl_sext(s, &id_src2->imm, &id_src2->imm, 2);
  printf("simm = %d  %x\n", id_src2->imm, id_src2->imm);
  printf("Run: dnpc(0x%08x) = (%s + %x) & (-1)\n", s->dnpc,paddtoname(dsrc1) , id_src2->imm);
  rtl_addi(s, &s->dnpc, dsrc1, id_src2->simm);
  s->dnpc = s->dnpc & (~1);
  printf("Ending def_EHelper: jalr, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(beq) {  
  printf("load the beq\n");
//  printf("!!!!\n");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  // printf("!!!!\n");
  printf("src1  src2 = %d %d\n", *dsrc1, *dsrc2);
  printf("simm = %d %u\n",id_dest->imm, id_dest->imm);
  if(*dsrc1 == *dsrc2) {
    if(*dsrc2 == 0) printf("Run: %s!= $0, \n", paddtoname(dsrc1));
    else printf("Run: %s == %s, dnpc += %x\n", paddtoname(dsrc1), paddtoname(dsrc2), id_dest->imm);
    s->dnpc = s->pc + id_dest->imm;
  } 
  else {
    if(*dsrc2 == 0) printf("Run: %s!= $0, \n", paddtoname(dsrc1));
    else printf("Run: %s != %s, \n", paddtoname(dsrc1), paddtoname(dsrc2));
  }
  printf("Ending def_EHelper: beq, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(bne) {
  printf("load the bne\n");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  // if(*dsrc2 == 0) panic("*dsrc2 == 0");
  // printf("src1  src2 = %d %d\n", *dsrc1, *dsrc2);
  printf("simm = %d %u\n",id_dest->imm, id_dest->imm);
  if(*dsrc1 != *dsrc2) {
    if(*dsrc2 == 0) {
      printf("Run: %s != 0, dnpc += %x\n", paddtoname(dsrc1), id_dest->imm);
    }
    else  printf("Run: %s != %s, dnpc += %x\n", paddtoname(dsrc1), paddtoname(dsrc2), id_dest->imm);
    s->dnpc = s->pc + id_dest->imm;
  } 
  else {
    if(*dsrc2 == 0) {
      printf("Run: %s == 0\n", paddtoname(dsrc1));
    }
    else printf("Run: %s == %s \n", paddtoname(dsrc1), paddtoname(dsrc2));
  }
  printf("Ending def_EHelper: bne, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(bge) {
  printf("load the bge\n");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  printf("*dsrc1 = %x, *dsrc2 = %x\n", *dsrc1, *dsrc2);
  printf("dsrc1 = %p, dsrc2 = %p\n", dsrc1, dsrc2);
  if((sword_t)*dsrc1 >= (sword_t) *dsrc2) {
    if(*dsrc1 == 0) {
      printf("Run: 0 >= %s, dnpc += %x\n", paddtoname(dsrc2), id_dest->imm);
    } else 
      printf("Run: %s >= %s, dnpc += %x\n", paddtoname(dsrc1), paddtoname(dsrc2), id_dest->imm);
    s->dnpc = s->pc + id_dest->imm;
  }  else {
    if(*dsrc1 == 0) 
      printf("Run: 0 < %s\n", paddtoname(dsrc2));
    else 
    printf("Run: %s < %s\n", paddtoname(dsrc1), paddtoname(dsrc2));
  }
  printf("Ending def_EHelper: bge, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(bgeu) {
  printf("load the bgeu\n");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  printf("*dsrc1 = %x, *dsrc2 = %x\n", *dsrc1, *dsrc2);
  printf("dsrc1 = %p, dsrc2 = %p\n", dsrc1, dsrc2);
  if(*dsrc1 >= *dsrc2) {
    if(*dsrc1 == 0) {
      printf("Run: 0 >= %s, dnpc += %x\n", paddtoname(dsrc2), id_dest->imm);
    } else 
      printf("Run: %s >= %s, dnpc += %x\n", paddtoname(dsrc1), paddtoname(dsrc2), id_dest->imm);
    s->dnpc = s->pc + id_dest->imm;
  }  else {
    if(*dsrc1 == 0) 
      printf("Run: 0 < %s\n", paddtoname(dsrc2));
    else 
    printf("Run: %s < %s\n", paddtoname(dsrc1), paddtoname(dsrc2));
  }
  printf("Ending def_EHelper: bgeu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(blt) {
  printf("load the blt");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  printf("*dsrc1 = %x, *dsrc2 = %x\n", *dsrc1, *dsrc2);
  if((sword_t) *dsrc1 < (sword_t)*dsrc2) {
    s->dnpc = s->pc + id_dest->imm;
  }
  printf("Ending def_EHelper: blt, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}

def_EHelper(bltu) {
  printf("load the bltu");
  rtl_sext(s, &id_dest->imm, &id_dest->imm, 2);
  printf("*dsrc1 = %x, *dsrc2 = %x\n", *dsrc1, *dsrc2);
  if(*dsrc1 < *dsrc2) {
    s->dnpc = s->pc + id_dest->imm;
  }
  printf("Ending def_EHelper: bltu, pc = %x, dnpc = %x\n", s->pc, s->dnpc);
  isa_reg_display();
}