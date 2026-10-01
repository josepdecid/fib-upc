(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project
     *
     * @description
     *
     */
    angular
        .module('project', [
            'ui.router',
            'pascalprecht.translate',
            'ngAnimate',
            'ngAria',
            'ngMessages',
            'ngMaterial',
            
            'project.home',
            'project.search',
            'project.manage',
            'project.settings',
            'project.about'
        ])
        .run(function ($rootScope) {

        });
}());

