(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.home.controller:HomeCtrl
     *
     * @description
     *
     */
    angular
        .module('project.home')
        .controller('HomeCtrl', HomeCtrl);

    function HomeCtrl($rootScope) {
        var vm = this;
        vm.ctrlName = 'HomeCtrl';
        vm.title = "MENU_HOME"

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.enabled = true;


        vm.isDocumentSelected = false;
        vm.recommendedDocs = JSON.parse($rootScope.backendService.getRecommendedDocs(5));
        vm.newDiscoveries = JSON.parse($rootScope.backendService.getNewDiscoveries(7));

        vm.select = function(document){
            vm.isDocumentSelected = true;
            vm.selectedDocument = document;
        }

        vm.back = function(){
            vm.isDocumentSelected = false;
            vm.documentSelected = undefined;
        }
    }


}());