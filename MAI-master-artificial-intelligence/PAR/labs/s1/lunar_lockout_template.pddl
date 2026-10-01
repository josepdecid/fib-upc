(define (problem lunar-lockout@)
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

;@ SPECIFIC PROBLEM @;
    )

    (:goal (at Red C3 C3))

    (:metric minimize (movements))
)