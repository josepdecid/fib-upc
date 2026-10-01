(define (domain lunar-lockout)
    (:requirements :strips :typing :adl :equality :fluents)

    (:types
        coord - object
        spacecraft - object
    )

    (:functions
        (movements)
    )

    (:predicates
        (at ?s - spacecraft ?x ?y - coord)
        (empty ?x ?y - coord)
        (next ?x ?y - coord)
        (adjacent ?x ?y - coord)
    )

    (:action move-up
        :parameters (?ship - spacecraft ?x ?y ?xtarget - coord)

        :precondition (and
            (at ?ship ?x ?y)                                        ; Spacecraft is at the given coordinates.
            (empty ?xtarget ?y)                                     ; The target cell is empty
            (next ?xtarget ?x)                                      ; The current cell x is below the target xtarget

            (exists (?limit - spacecraft ?xlimit - coord) (and      ; It exists an spacecraft that limits the movement
                (at ?limit ?xlimit ?y)                              ; located at <xblock, y> (same column)
                (adjacent ?xlimit ?xtarget)                         ; right above the target cell.
            ))

            (forall (?obstacle - spacecraft ?xobstacle - coord) 
                (not (and                                           ; Is not valid if:
                    (not (= ?ship ?obstacle))                       ; 1) The obstacle is the same spacecraft
                    (at ?obstacle ?xobstacle ?y)                    ; 2) There is an obstacle at <xobstaacle, y>
                    (next ?xtarget ?xobstacle)                      ;    - that is below the xblock 
                    (not (next ?x ?xobstacle))                      ;    - and above the spaceraft x
                ))
            )
        )

        :effect (and
            (not (at ?ship ?x ?y)) (empty ?x ?y)                    ; We remove the ship from the current cell and mark it as empty.
            (at ?ship ?xtarget ?y) (not (empty ?xtarget ?y))        ; We set the ship in the new cell and unmark it as empty.
            (increase (movements) 1)
        )
    )

    (:action move-down
        :parameters (?ship - spacecraft ?x ?y ?xtarget - coord)

        :precondition (and
            (at ?ship ?x ?y)                                        ; Spacecraft is at the given coordinates.
            (empty ?xtarget ?y)                                     ; The target cell is empty
            (next ?x ?xtarget)                                      ; The target cell xtarget is below the current x

            (exists (?limit - spacecraft ?xlimit - coord) (and      ; It exists an spacecraft that limits the movement
                (at ?limit ?xlimit ?y)                              ; located at <xblock, y> (same column)
                (adjacent ?xtarget ?xlimit)                         ; right above the target cell.
            ))

            (forall (?obstacle - spacecraft ?xobstacle - coord) 
                (not (and                                           ; Is not valid if:
                    (not (= ?ship ?obstacle))                       ; 1) The obstacle is the same spacecraft
                    (at ?obstacle ?xobstacle ?y)                    ; 2) There is an obstacle at <xobstaacle, y>
                    (next ?xobstacle ?xtarget)                      ;    - that is below the xblock 
                    (not (next ?xobstacle ?x))                      ;    - and above the spaceraft x
                ))
            )
        )

        :effect (and
            (not (at ?ship ?x ?y)) (empty ?x ?y)                    ; We remove the ship from the current cell and mark it as empty.
            (at ?ship ?xtarget ?y) (not (empty ?xtarget ?y))        ; We set the ship in the new cell and unmark it as empty.
            (increase (movements) 1)
        )
    )

    (:action move-left
        :parameters (?ship - spacecraft ?x ?y ?ytarget - coord)

        :precondition (and
            (at ?ship ?x ?y)                                        ; Spacecraft is at the given coordinates.
            (empty ?x ?ytarget)                                     ; The target cell is empty
            (next ?ytarget ?y)                                      ; The target cell ytarget is before the current y

            (exists (?limit - spacecraft ?ylimit - coord) (and      ; It exists an spacecraft that limits the movement
                (at ?limit ?x ?ylimit)                              ; located at <x, yblock> (same row)
                (adjacent ?ylimit ?ytarget)                         ; right before the target cell.
            ))

            (forall (?obstacle - spacecraft ?yobstacle - coord) 
                (not (and                                           ; Is not valid if:
                    (not (= ?ship ?obstacle))                       ; 1) The obstacle is the same spacecraft
                    (at ?obstacle ?x ?yobstacle)                    ; 2) There is an obstacle at <xobstaacle, y>
                    (next ?ytarget ?yobstacle)                      ;    - that is after the ytarget 
                    (not (next ?y ?yobstacle))                      ;    - and before the spaceraft y
                ))
            )
        )

        :effect (and
            (not (at ?ship ?x ?y)) (empty ?x ?y)                    ; We remove the ship from the current cell and mark it as empty.
            (at ?ship ?x ?ytarget) (not (empty ?x ?ytarget))        ; We set the ship in the new cell and unmark it as empty.
            (increase (movements) 1)
        )
    )

    (:action move-right
        :parameters (?ship - spacecraft ?x ?y ?ytarget - coord)

        :precondition (and
            (at ?ship ?x ?y)                                        ; Spacecraft is at the given coordinates.
            (empty ?x ?ytarget)                                     ; The target cell is empty
            (next ?y ?ytarget)                                      ; The target cell ytarget is before the current y

            (exists (?limit - spacecraft ?ylimit - coord) (and      ; It exists an spacecraft that limits the movement
                (at ?limit ?x ?ylimit)                              ; located at <x, yblock> (same row)
                (adjacent ?ytarget ?ylimit)                         ; right before the target cell.
            ))

            (forall (?obstacle - spacecraft ?yobstacle - coord) 
                (not (and                                           ; Is not valid if:
                    (not (= ?ship ?obstacle))                       ; 1) The obstacle is the same spacecraft
                    (at ?obstacle ?x ?yobstacle)                    ; 2) There is an obstacle at <xobstacle, y>
                    (next ?yobstacle ?ytarget)                      ;    - that is after the ytarget 
                    (not (next ?yobstacle ?y))                      ;    - and before the spaceraft y
                ))
            )
        )

        :effect (and
            (not (at ?ship ?x ?y)) (empty ?x ?y)                    ; We remove the ship from the current cell and mark it as empty.
            (at ?ship ?x ?ytarget) (not (empty ?x ?ytarget))        ; We set the ship in the new cell and unmark it as empty.
            (increase (movements) 1)
        )
    )
)

