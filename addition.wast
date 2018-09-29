(module
  (export "add" (func $org/ea/Code.add))
  (func $org/ea/Code.add (param i32) (param i32) (result i32)
    get_local 0
    get_local 1
    i32.add
    i32.const 4
    i32.add
    return
  )
)
