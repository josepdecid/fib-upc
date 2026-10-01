(function () {
    'use strict';

    angular
        .module('project.about')
        .config(config);

    function config($stateProvider) {
        $stateProvider
            .state('project.about', {
                url: '/about',
                parent: 'project',
                views: {
                    'wrapper': {
                        templateUrl: 'about/about.tpl.html',
                        controller: 'AboutCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
    }
}());

