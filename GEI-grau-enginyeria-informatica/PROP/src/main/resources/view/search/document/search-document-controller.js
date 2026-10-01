(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.search.document.controller:SearchDocumentCtrl
     *
     * @description
     *
     */
    angular
        .module('project.search')
        .controller('SearchDocumentCtrl', SearchDocumentCtrl);

    function SearchDocumentCtrl($rootScope, $mdDialog) {
        var vm = this;
        vm.ctrlName = 'SearchDocumentCtrl';

        vm.title = "MENU_SEARCH_SINGLE_DOCUMENT";

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.search = true;
        $rootScope.toolbarParams.enabled = true;

        (function showDialog() {
            $mdDialog.show({
                controller: DialogDocumentController,
                templateUrl: 'search/document/search-document-dialog.tpl.html',
                clickOutsideToClose: false,
                escapeToClose: false
            })}());

        function DialogDocumentController($rootScope, $scope, $mdDialog) {
            $scope.searchDocument = function (title, author) {
                try {
                    vm.isInvalidData = undefined;
                    var response = $rootScope.backendService.getDocumentByTitleAndAuthor(title, author);
                    vm.documentSelected = JSON.parse(response);
                    vm.isDocumentSelected = true;
                    $mdDialog.hide();
                } catch (e) {
                    if (e.toString().indexOf('DocumentNotFoundException') !== -1) {
                        $scope.isInvalidData = 'EXCEPTION_DOCUMENT_NOT_FOUND';
                    }
                }
            }
        }

    }
}());