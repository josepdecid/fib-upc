(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.about.controller:AboutCtrl
     *
     * @description
     *
     */
    angular
        .module('project.about')
        .controller('AboutCtrl', AboutCtrl);

    function AboutCtrl($rootScope, $mdDialog) {
        var vm = this;
        vm.ctrlName = 'AboutCtrl';

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = "About";
        $rootScope.toolbarParams.enabled = true;

        vm.unlockTit = function () {
            $mdDialog.show({
                template: '<img src="https://i.imgflip.com/1ftr9m.jpg"">',
                zIndex: 2000,
                clickOutsideToClose: true,
                escapeToClose: true
            });
        };
    }
}());