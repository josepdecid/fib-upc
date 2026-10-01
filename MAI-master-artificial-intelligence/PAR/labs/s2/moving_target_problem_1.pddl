(define (problem moving-target1)
    (:domain moving-target)
    
    (:objects 
        R - robot
        G - ghost

		C0 C1 C2 C3 - coord
		T0 T1 T2 T3 - time
    )

    (:init
		(next C0 C1) (next C1 C0)
		(next C1 C2) (next C2 C1)
		(next C2 C3) (next C3 C2)

		(next T0 T1)
		(next T1 T2)
		(next T2 T3)

        (= path-cost 0)

		(= (cost C0 C0) 1) (= (cost C0 C1) 1) (= (cost C0 C2) 1) (= (cost C0 C3) 1)
		(= (cost C1 C0) 1) (= (cost C1 C1) 1) (= (cost C1 C2) 1) (= (cost C1 C3) 1)
		(= (cost C2 C0) 1) (= (cost C2 C1) 1) (= (cost C2 C2) 1) (= (cost C2 C3) 1)
		(= (cost C3 C0) 1) (= (cost C3 C1) 1) (= (cost C3 C2) 1) (= (cost C3 C3) 1)

		(at R C0 C0 T0)
		(at G C3 C3 T0)

		(scheduled C3 C3 T0)
		(scheduled C2 C3 T1)
		(scheduled C1 C3 T2)
		(scheduled C1 C2 T3)
    )

    (:goal (exists (?x ?y - coord ?t - time) (and (at R ?x ?y ?t) (at G ?x ?y ?t))))

    (:metric minimize (path-cost))
)
