(set-logic QF_LIRAFS)
(set-info :status sat)
(declare-fun s () (Set Real))
(declare-fun t3 () (Set Real))
(assert (or (member 1.0 t3) (member 0.0 s)))
(assert (not (= t3 (setminus s (singleton 1.0)))))
(check-sat)
