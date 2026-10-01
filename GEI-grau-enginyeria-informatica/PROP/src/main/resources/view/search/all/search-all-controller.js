(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.search.all.controller:SearchAllCtrl
     *
     * @description
     *
     */
    angular
        .module('project.search')
        .controller('SearchAllCtrl', SearchAllCtrl);

    function SearchAllCtrl($rootScope) {
        var vm = this;
        vm.ctrlName = 'SearchAllCtrl';
        vm.title = 'MENU_SEARCH_ALL';

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.enabled = true;

        vm.isDocumentSelected = false;

        var response = $rootScope.backendService.searchForAllDocuments();
        vm.documents = JSON.parse(response);

        vm.selectDocument = function(document){
            vm.documentSelected = document;
            vm.isDocumentSelected = true;
        };

        vm.back = function(){
            vm.isDocumentSelected = false;
        }
    }
}());