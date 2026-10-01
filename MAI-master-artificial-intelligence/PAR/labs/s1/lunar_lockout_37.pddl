(define (problem lunar-lockout37)
    (:domain lunar-lockout)
    
    (:objects
        Red Orange Yellow Green Blue Purple - spacecraft
        C1 C2 C3 C4 C5 - coord
    )

    (:init
        ; Grid definition

        (= (movements) 0)

        (adjacent C1 C2)
        (next C1 C2) (next C1 C3) (next C1 C4) (next C1 C5)
        
        (adjacent C2 C3)
        (next C2 C3) (next C2 C4) (next C2 C5)
        
        (adjacent C3 C4)
        (next C3 C4) (next C3 C5)
        
        (adjacent C4 C5)
        (next C4 C5)

        ; Problem custom definition

		(at Orange C1 C1)
		(at Green C1 C4)
		(at Purple C1 C5)
		(at Yellow C4 C1)
		(at Red C4 C4)

		(empty C1 C2)
		(empty C1 C3)
		(empty C2 C1)
		(empty C2 C2)
		(empty C2 C3)
		(empty C2 C4)
		(empty C2 C5)
		(empty C3 C1)
		(empty C3 C2)
		(empty C3 C3)
		(empty C3 C4)
		(empty C3 C5)
		(empty C4 C2)
		(empty C4 C3)
		(empty C4 C5)
		(empty C5 C1)
		(empty C5 C2)
		(empty C5 C3)
		(empty C5 C4)
		(empty C5 C5)
    )

    (:goal (at Red C3 C3))

    (:metric minimize (movements))
)