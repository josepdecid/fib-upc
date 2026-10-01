(define (domain moving-target)
    (:requirements :strips :fluents)

    (:types
        value - object
        coord time - value

        player - object
        robot ghost - player
    )

    (:predicates
        (at ?p - player ?x ?y - coord ?t - time)        ; Player is at (x, y) at t
        (scheduled ?x ?y - coord ?t - time)             ; Ghost will be at (x, y) at t
        (next ?a ?b - value)                            ; B is right after A
    )


    (:functions
        (cost ?x - coord ?y - coord)                    ; Cost to visit each cell
        (path-cost)                                     ; Total cost of the path
    )

    (:action move
        :parameters (?r - robot ?xr ?yr ?xrn ?yrn - coord
                     ?g - ghost ?xg ?yg ?xgn ?ygn - coord
                     ?t ?tn - time)

        :precondition (and
            (at ?r ?xr ?yr ?t)                          ; Robot at (xr, yr) at t
            (at ?g ?xg ?yg ?t)                          ; Ghost at (xg, yg) at t

            (next ?t ?tn)                               ; tn = t + 1
            (scheduled ?xgn ?ygn ?tn)                   ; Ghost at (xgn, ygn) at tn
            
            (or                                         ; Next robot position:
                (and (= ?xr ?xrn) (next ?yr ?yrn))          ; - Adjacent on left or right
                (and (next ?xr ?xrn) (= ?yr ?yrn))          ; - Adjacent on top or bottom
                (and (= ?xr ?xrn) (= ?yr ?yrn))             ; - Remain same cell
            )
        )

        :effect (and
            (not (at ?r ?xr ?yr ?t))                    ; Robot not anymore at (xr, yr)
            (at ?r ?xrn ?yrn ?tn)                       ; Robot is now at (xrn, yrn)

            (not (at ?g ?xg ?yg ?t))                    ; Ghost not anymore at (xg, yg)
            (at ?g ?xgn ?ygn ?tn)                       ; Ghost is now at (xgn, ygn)

            (increase (path-cost) (cost ?xrn ?yrn))     ; Add the new cell cost to the total cost
        )
    )
)