(set-logic QF_BVLIA)
(set-info :status sat)
(declare-fun a () (_ BitVec 1))
(assert (< (bv2nat a) 1))
(check-sat)
