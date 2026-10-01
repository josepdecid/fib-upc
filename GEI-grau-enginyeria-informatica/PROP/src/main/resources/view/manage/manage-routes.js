(function () {
    'use strict';

    angular
        .module('project.manage')
        .config(config);

    function config($stateProvider) {
        $stateProvider
            .state('project.manage', {
                url: '/manage',
                parent: 'project',
                abstract: true,
                views: {
                    'wrapper': {
                        templateUrl: 'manage/manage.tpl.html'
                    }
                }
            })
            .state('project.manage.all', {
                url: '/all',
                parent: 'project.manage',
                views: {
                    'manage-content': {
                        templateUrl: 'manage/all/manage-all.tpl.html',
                        controller: 'ManageAllCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
            .state('project.manage.favourites', {
                url: '/favourites',
                parent: 'project.manage',
                views: {
                    'manage-content': {
                        templateUrl: 'manage/favourites/manage-favourites.tpl.html',
                        controller: 'ManageFavouritesCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
    }
}());

