def_EHelper(lui) {
  printf("pc == %x\n", s->pc);
  printf("lui 前 ddest == %x\n", *ddest);
  rtl_li(s, ddest, id_src1->imm);
  printf("lui 后 ddest == %x\n", *ddest);
}

def_EHelper(addi) {
  printf("pc == %x\n", s->pc);
  printf("addi 前 ddest == %x\n", *ddest); 
  rtl_mv(s, ddest, id_src1->preg);
  printf("addi 中 ddest == %x\n", *ddest);
  rtl_addi(s, ddest, ddest, id_src2->imm);
  printf("addi 后 ddest == %x\n", *ddest);
}

def_EHelper(auipc) {
  printf("pc == %x\n", s->pc);
  printf("auipc 前 ddest == %x\n", *ddest);
  rtl_add(s, ddest, &s->pc, &id_src1->imm);
  printf("auipc 后 ddest == %x\n", *ddest);
}

def_EHelper(jal) {
  rtl_li(s, ddest, s->pc + 4);
  printf("id_src2->imm == %x\n", id_src2->imm);
  printf("pc == %x\n", s->pc);
  rtl_addi(s, &s->dnpc, &s->pc, id_src2->imm);
  // s->dnpc = s->pc + id_src2->imm; 
  printf("dnpc is %x\n", s->dnpc);
}

def_EHelper(jarl) {
  
}