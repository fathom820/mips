.text
addiu   $s2, $s2, 2
div     $s5, $s2, $s5
slti    $s5, $s1, 3
or      $t0, $t0, 1
subu    $t0, $s5, $s2