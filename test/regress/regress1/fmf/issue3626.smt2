; COMMAND-LINE: --fmf-bound
; EXPECT: sat
(set-logic ALL)
(assert (forall ((a Int)) (or (distinct (/ 0 0) a) (= (/ 0 a) 0))))
(check-sat)
