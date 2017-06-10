
_DEFINE_OP(MUL_ADD_F32)
{
  vm->gpr[_RD(op)].f32() = vm->gpr[_RS(op)].f32()*vm->gpr[_EX_U8_1].f32() + vm->gpr[_EX_U8_2].f32() ;
  ++vm->pc.extU16;
}
_END_OP

_DEFINE_OP(MUL_ADD_F64)
{
  vm->gpr[_RD(op)].f64() = vm->gpr[_RS(op)].f64()*vm->gpr[_EX_U8_1].f64() + vm->gpr[_EX_U8_2].f64() ;
  ++vm->pc.extU16;
}
_END_OP

