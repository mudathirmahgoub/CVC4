(set-option :incremental false)
(set-info :status unsat)
(set-logic QF_BV)
(declare-fun v1 () (_ BitVec 12))
(declare-fun v15 () (_ BitVec 8))
(declare-fun v11 () (_ BitVec 12))
(declare-fun v12 () (_ BitVec 15))
(check-sat-assuming ( (let ((_let_0 ((_ sign_extend 2) ((_ sign_extend 1) v1)))) (let ((_let_1 (bvxnor v12 _let_0))) (let ((_let_2 (ite (bvult _let_0 _let_1) (_ bv1 1) (_ bv0 1)))) (let ((_let_3 (ite (distinct (_ bv1 15) ((_ zero_extend 14) (bvcomp v11 ((_ zero_extend 4) v15)))) (_ bv1 1) (_ bv0 1)))) (and (not (bvslt (_ bv0 12) v1)) (not (bvult (_ bv0 1) (ite (bvult ((_ sign_extend 3) (ite (= (_ bv1 1) (ite (bvult v11 (_ bv1 12)) (_ bv1 1) (_ bv0 1))) v11 (_ bv0 12))) v12) (_ bv1 1) (_ bv0 1)))) (bvult (_ bv0 5) ((_ repeat 5) _let_2)) (= (_ bv0 10) ((_ sign_extend 9) (ite (bvsge _let_1 (_ bv0 15)) (_ bv1 1) (_ bv0 1)))) (bvugt (bvadd (_ bv1 14) ((_ zero_extend 13) (ite (bvult _let_2 (_ bv1 1)) (_ bv1 1) (_ bv0 1)))) (_ bv0 14)) (or false (bvsgt (_ bv0 12) (bvxor v1 ((_ sign_extend 11) _let_3))) (bvule ((_ zero_extend 12) _let_3) (_ bv0 13))) (bvuge ((_ sign_extend 14) (ite (bvugt (bvadd (_ bv1 1) (ite (bvsle (_ bv0 12) v1) (_ bv1 1) (_ bv0 1))) (_ bv0 1)) (_ bv1 1) (_ bv0 1))) (_ bv1 15))))))) ))
