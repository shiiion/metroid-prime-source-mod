    .machine ppc
    .section ".text"

    .type _save_reg_ctx, @function
    .globl _save_reg_ctx
_save_reg_ctx:
    .cfi_startproc
    stmw 14, 0(3)
    blr
    .cfi_endproc

    .globl _restore_reg_ctx
    .type _restore_reg_ctx, @function
_restore_reg_ctx:
    .cfi_startproc
    lmw 14, 0(3)
    blr
    .cfi_endproc
