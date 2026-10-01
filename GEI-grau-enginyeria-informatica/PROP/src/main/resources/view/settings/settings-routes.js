(function () {
    'use strict';

    angular
        .module('project.settings')
        .config(config);

    function config($stateProvider) {
        $stateProvider
            .state('project.settings', {
                url: '/settings',
                parent: 'project',
                views: {
                    'wrapper': {
                        templateUrl: 'settings/settings.tpl.html',
                        controller: 'SettingsCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
    }
}());

