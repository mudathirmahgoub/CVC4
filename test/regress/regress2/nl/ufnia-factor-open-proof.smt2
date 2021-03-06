(set-logic QF_UFNIA)
(set-info :status unsat)
(declare-fun pow2 (Int) Int)
(define-fun intmax ((k Int)) Int (- (pow2 k) 1))
(define-fun intmodtotal ((pow2 Int) (a Int) (b Int)) Int (mod a b))
(define-fun intneg ((k Int) (a Int)) Int 1)
(define-fun intmul ((k Int) (a Int) (b Int)) Int (mod (* a b) (pow2 k)))
(declare-fun k () Int)
(assert (> k 0))
(assert (= 1 (pow2 1)))
(declare-fun %x () Int)
(assert (> %x 0))
(assert (not (= (intmul k %x (intmax k)) (mod (- (pow2 k) %x) (pow2 k)))))
(check-sat)
