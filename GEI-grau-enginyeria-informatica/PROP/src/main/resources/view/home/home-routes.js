(function () {
    'use strict';

    angular
        .module('project.home')
        .config(config);

    function config($stateProvider) {
        $stateProvider
            .state('project.home', {
                url: '/home',
                parent: 'project',
                views: {
                    'wrapper': {
                        templateUrl: 'home/home.tpl.html',
                        controller: 'HomeCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
    }
}());

