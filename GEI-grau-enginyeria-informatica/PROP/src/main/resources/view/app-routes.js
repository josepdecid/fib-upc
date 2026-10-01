(function () {
    'use strict';

    angular
        .module('project')
        .config(config)
        .run(['$rootScope', '$state', '$stateParams',
            function ($rootScope, $state, $stateParams) {
                $rootScope.$state = $state;
                $rootScope.$stateParams = $stateParams;
            }
        ]);

    function config($stateProvider, $urlRouterProvider) {

        $stateProvider
            .state('project', {
                url: '/project',
                views: {
                    'body': {
                        templateUrl: 'project.tpl.html',
                        controller: 'AppCtrl',
                        controllerAs: 'vm'
                    }
                }
            });

        $urlRouterProvider.otherwise('/project');
    }

}());
