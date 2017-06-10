
_DEFINE_OP(NOP)
{

}
_END_OP

_DEFINE_OP(BRK)
{
  vm->status = VMDefs::BREAKPOINT;
  _THROW(-1)
}
_END_OP

_DEFINE_OP(SET_IS)
{
  vm->status = VMDefs::UPDATE_INST_SET;
  _THROW(-1)
}
_END_OP

