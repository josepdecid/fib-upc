(define (domain ricoRico)
  (:requirements :strips :typing :adl)
  (:types
    day - object
    dish - object
    mainCourse - dish secondCourse - dish
  )

  (:predicates
    (incompatible ?mc - mainCourse ?sc - secondCourse)
    (assigned ?d - day ?mc - mainCourse ?sc - secondCourse)
    (dayReady ?d - day)
  )

  (:action assignMenus
    :parameters (?d - day ?mc - mainCourse ?sc - secondCourse)
    :precondition (not (incompatible ?mc ?sc))
    :effect (and (dayReady ?d) (assigned ?d ?mc ?sc))
  )
)
