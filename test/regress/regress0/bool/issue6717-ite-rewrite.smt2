(set-logic ALL)
(declare-fun T () Bool)
(declare-fun v () String)
(assert (ite T T true))
(assert (or T (and (str.prefixof v "") (exists ((x Int)) (= "t" (str.substr v 0 x))))))
(set-info :status sat)
(check-sat)
