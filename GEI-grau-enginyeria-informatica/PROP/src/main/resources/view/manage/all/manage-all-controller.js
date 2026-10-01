(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.manage.controller:ManageAllCtrl
     *
     * @description
     *
     */
    angular
        .module('project.manage')
        .controller('ManageAllCtrl', ManageAllCtrl);

    function ManageAllCtrl($rootScope) {
        var vm = this;
        vm.ctrlName = 'ManageAllCtrl';
        vm.title = 'MENU_MANAGEMENT_ALL';

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.enabled = true;

        var response = $rootScope.backendService.getCurrentUserDocuments();
        vm.documents = JSON.parse(response);
    }
}());