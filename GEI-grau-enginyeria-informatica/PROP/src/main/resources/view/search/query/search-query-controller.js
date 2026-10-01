(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.search.author.controller:SearchQueryCtrl
     *
     * @description
     *
     */
    angular
        .module('project.search')
        .controller('SearchQueryCtrl', SearchQueryCtrl);

    function SearchQueryCtrl($mdDialog) {
        var vm = this;
        vm.ctrlName = 'SearchQueryCtrl';

        vm.title = 'MENU_SEARCH_QUERY';

        vm.isDocumentSelected = false;

        (function showDialog() {
            $mdDialog.show({
                controller: DialogBooleanController,
                templateUrl: 'search/query/search-query-dialog.tpl.html',
                clickOutsideToClose: false,
                escapeToClose: false
            })}());

        function DialogBooleanController($rootScope, $scope, $mdDialog) {

            $scope.searchMode1 = 'Normal mode';
            $scope.searchMode2 = 'Super mode';
            $scope.searchMode = {
                mode: $scope.searchMode1
            };

            $scope.similarDocuments = undefined;

            $scope.searchQuery = function (query, numberOfDocuments) {
                try {
                    $scope.isInvalidData = undefined;
                    var response = $rootScope.backendService.getDocumentsByQuery(query, numberOfDocuments, $scope.searchMode.mode === $scope.searchMode2);
                    $scope.similarDocuments = JSON.parse(response);
                    if($scope.similarDocuments.length==0){
                        $scope.similarDocuments = undefined;
                        $scope.isInvalidData = 'NO_DOCUMENTS_FOUND';
                    }
                } catch (e) {
                    if (e.toString().indexOf('InvalidQueryException') !== -1) {
                        $scope.isInvalidData = 'EXCEPTION_INVALID_QUERY';
                    }
                }
            };

            $scope.selectNewDocument = function (document) {
                vm.documentSelected = document;
                vm.isDocumentSelected = true;
                $mdDialog.hide();
            };

        }

    }

}());
