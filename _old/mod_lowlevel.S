    .machine ppc
    .extern shutdown_signal

    .section ".text"
    .align 2

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

/*
 * Callgating scheme:
 * Any hook type (bl, vft, trampoline) will relocate to an entry in this callgate table
 * which will prepare r12 with the location to dispatch to
 *
 * _callgate_dispatch will then query the mod's shutdown_signal to check if it is
 * currently un-initialized and awaiting original instruction restoration from the ElfModLoader
 *
 * If the signal is 0, we're good to dispatch to the hook target, otherwise we should forward
 * to the original function
 */
    .globl _callgate_table
    .type _callgate_table, @function
_callgate_table:
    .cfi_startproc
    .zero 12288
    .cfi_endproc
    .size _callgate_table, .-_callgate_table

    .globl _trampoline_restore_table
    .type _trampoline_restore_table @function
_trampoline_restore_table:
    .cfi_startproc
    .zero 8192
    .cfi_endproc
    .size _trampoline_restore_table, .-_trampoline_restore_table

    .globl _callgate_dispatch
    .type _callgate_dispatch, @function
_callgate_dispatch:
    .cfi_startproc
    lis 12, shutdown_signal@ha
    lwz 12, shutdown_signal@l(12)
    cmpwi 12, 0
    beq _callgate_dispatch_runhook
    lwz 11, 0(11)
    b _callgate_dispatch_end
_callgate_dispatch_runhook:
    lwz 11, 4(11)
_callgate_dispatch_end:
    mtctr 11
    bctr
    .cfi_endproc
    .size _callgate_dispatch, .-_callgate_dispatch


    .section ".bss"
    .align 2

/*
 * Table of function addresses, organized in pairs
 * effectively array of 1024 pairs of addresses :: (original fn, hooked fn)
 */
    .type _mod_dispatch_table, @object
    .size _mod_dispatch_table, 8192
_mod_dispatch_table:
    .zero 8192
    

