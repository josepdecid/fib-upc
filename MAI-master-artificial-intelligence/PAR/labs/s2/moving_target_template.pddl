(define (problem moving-target)
    (:domain moving-target)
    
    (:objects 
        R - robot
        G - ghost

{% COORDS %}
{% TIMESTEPS %}
    )

    (:init
{% NEXT_COORDS %}

{% NEXT_TIMESTEPS %}

        (= path-cost 0)

{% COSTS %}

{% ROBOT %}
{% GHOST %}

{% SCHEDULE %}
    )

    (:goal (exists (?x ?y - coord ?t - time) (and (at R ?x ?y ?t) (at G ?x ?y ?t))))

    (:metric minimize (path-cost))
)
