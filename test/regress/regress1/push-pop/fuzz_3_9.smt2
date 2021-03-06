; COMMAND-LINE: --incremental --no-produce-proofs
; EXPECT: sat
; EXPECT: sat
; EXPECT: sat
; EXPECT: sat
; EXPECT: sat
; EXPECT: sat
; EXPECT: sat
; EXPECT: unsat
; EXPECT: sat
(set-logic QF_LRA)
(declare-fun x0 () Real)
(declare-fun x1 () Real)
(declare-fun x2 () Real)
(assert (or (not (>= (+ (* (- 32) x2 ) (* (- 10) x0 ) (* (- 33) x0 ) (* 16 x1 ) ) (- 35))) (< (+ (* (- 46) x1 ) (* 44 x1 ) (* (- 15) x1 ) (* (- 22) x2 ) ) (- 20)) ))
(check-sat)
(push 1)
(assert (or (not (< (+ (* (- 1) x2 ) (* (- 26) x0 ) ) 32)) (> (+ (* 39 x1 ) (* 31 x1 ) (* (- 16) x0 ) ) 27) ))
(check-sat)
(pop 1)
(assert (or (> (+ (* 46 x1 ) (* 48 x1 ) (* 26 x0 ) ) 12) (= (+ (* 30 x1 ) (* 1 x0 ) (* 8 x2 ) (* 11 x2 ) ) (- 3)) ))
(assert (<= (+ (* (- 11) x1 ) (* (- 27) x2 ) (* (- 29) x2 ) (* 23 x1 ) ) 19) )
(assert (not (> (+ (* 15 x0 ) (* 25 x1 ) ) 47)) )
(assert (<= (+ (* (- 3) x2 ) (* 1 x1 ) (* 36 x1 ) ) (- 27)) )
(check-sat)
(push 1)
(assert (not (<= (+ (* (- 3) x0 ) (* (- 33) x2 ) (* 7 x2 ) (* (- 37) x0 ) ) 13)) )
(check-sat)
(pop 1)
(assert (or (not (> (+ (* 24 x2 ) (* (- 48) x0 ) (* 18 x1 ) ) (- 46))) (not (< (+ (* (- 31) x1 ) (* 18 x0 ) (* (- 32) x0 ) (* (- 9) x0 ) ) 37)) ))
(assert (or (not (< (+ (* (- 30) x2 ) (* (- 32) x0 ) (* 27 x0 ) ) 28)) (not (= (+ (* (- 20) x2 ) (* (- 10) x2 ) ) (- 3))) (<= (+ (* 42 x0 ) (* 49 x0 ) (* 28 x0 ) (* 0 x2 ) ) (- 30)) ))
(assert (or (not (<= (+ (* 15 x2 ) (* 22 x2 ) ) (- 7))) (< (+ (* (- 7) x1 ) (* (- 42) x0 ) (* (- 27) x2 ) (* 19 x2 ) ) 15) (< (+ (* (- 25) x1 ) (* 39 x2 ) (* (- 24) x1 ) (* 17 x1 ) ) (- 48)) ))
(assert (or (= (+ (* (- 49) x0 ) (* 27 x1 ) (* 16 x0 ) (* (- 26) x2 ) ) (- 24)) (<= (+ (* (- 33) x0 ) (* (- 7) x1 ) (* (- 7) x2 ) (* 1 x0 ) ) 34) ))
(assert (not (<= (+ (* 30 x0 ) (* 17 x0 ) (* (- 48) x0 ) ) 19)) )
(check-sat)
(push 1)
(check-sat)
(pop 1)
(assert (or (not (= (+ (* 24 x2 ) (* 13 x2 ) (* (- 13) x0 ) (* 14 x2 ) ) 8)) (> (+ (* (- 30) x2 ) (* (- 32) x1 ) (* (- 45) x0 ) (* (- 2) x2 ) ) 15) ))
(assert (or (> (+ (* (- 9) x0 ) (* (- 21) x1 ) ) 3) (not (= (+ (* (- 26) x2 ) (* 3 x0 ) ) (- 10))) ))
(assert (or (not (> (+ (* (- 20) x0 ) (* 43 x0 ) ) (- 14))) (> (+ (* 13 x1 ) (* (- 38) x1 ) (* 4 x1 ) (* (- 12) x2 ) ) (- 15)) (not (< (+ (* (- 38) x2 ) (* (- 3) x0 ) ) 15)) ))
(assert (or (>= (+ (* (- 33) x0 ) (* 8 x1 ) (* 16 x0 ) ) 32) (not (<= (+ (* 23 x0 ) (* (- 28) x0 ) (* 30 x1 ) (* 17 x2 ) ) 41)) (>= (+ (* 28 x1 ) (* (- 42) x0 ) ) (- 12)) ))
(assert (or (not (<= (+ (* 23 x1 ) (* 20 x2 ) (* (- 34) x0 ) (* (- 40) x2 ) ) 28)) (not (= (+ (* 17 x2 ) (* 30 x2 ) ) (- 15))) (<= (+ (* (- 47) x1 ) (* (- 24) x0 ) (* (- 37) x0 ) ) 19) ))
(assert (or (= (+ (* 14 x0 ) (* (- 22) x1 ) ) 30) (<= (+ (* 28 x1 ) (* 33 x2 ) (* 49 x2 ) ) (- 35)) (<= (+ (* (- 47) x0 ) (* (- 45) x2 ) (* (- 7) x1 ) (* (- 47) x1 ) ) 47) ))
(check-sat)
(push 1)
(assert (or (not (> (+ (* 35 x2 ) (* (- 46) x0 ) ) 26)) (>= (+ (* 3 x1 ) (* 1 x2 ) (* (- 14) x0 ) ) 27) (> (+ (* (- 27) x2 ) (* 20 x2 ) (* 19 x1 ) (* 23 x2 ) ) 39) ))
(assert (or (not (> (+ (* 20 x0 ) (* 9 x2 ) ) 6)) (not (< (+ (* 19 x1 ) (* (- 45) x1 ) ) (- 45))) ))
(check-sat)
(pop 1)
(check-sat)
(push 1)
