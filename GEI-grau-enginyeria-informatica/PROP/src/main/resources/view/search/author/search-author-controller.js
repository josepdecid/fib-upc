(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.search.author.controller:SearchAuthorCtrl
     *
     * @description
     *
     */
    angular
        .module('project.search')
        .controller('SearchAuthorCtrl', SearchAuthorCtrl);

    function SearchAuthorCtrl($rootScope, $mdDialog) {
        var vm = this;
        vm.ctrlName = 'SearchAuthorCtrl';

        vm.title = 'MENU_SEARCH_AUTHOR';

        //TOOLBAR CONFIG
        $rootScope.resetToolbar();
        $rootScope.toolbarParams.title = vm.title;
        $rootScope.toolbarParams.search = true;
        $rootScope.toolbarParams.enabled = true;

        vm.selectDocument = function (document) {
            vm.documentSelected = document;
            vm.isAuthorSelected = false;
            vm.isDocumentSelected = true;
        };

        vm.back = function(){
            vm.isDocumentSelected = false;
            vm.isAuthorSelected = true;
        };

        (function showDialog() {
            $mdDialog.show({
                controller: DialogAuthorsController,
                templateUrl: 'search/author/search-author-dialog.tpl.html',
                clickOutsideToClose: false,
                escapeToClose: false
            })}());

        function DialogAuthorsController($rootScope, $scope, $mdDialog) {
            $scope.searchAuthors = function (prefix) {
                $scope.authors = undefined;
                $scope.isInvalidData = undefined;
                prefix = prefix || '';

                try {
                    var response = $rootScope.backendService.getAuthorsWithPrefix(prefix);
                    $scope.authors = JSON.parse(response).authors;
                    $scope.isPrefixSearch = true;
                } catch (e) {
                    if (e.toString().indexOf('AuthorNotFoundException') !== -1) {
                        $scope.isInvalidData = 'EXCEPTION_AUTHOR_NOT_FOUND';
                    }
                }
            };
            $scope.selectAuthor = function (author) {
                try {
                    var response = $rootScope.backendService.getDocumentsByAuthorId(author.name);
                    vm.documents = JSON.parse(response);
                    vm.isAuthorSelected = true;
                    $mdDialog.hide();
                } catch (e) {
                    if (e.toString().indexOf('AuthorNotFoundException') !== -1) {
                        $scope.isInvalidData = 'EXCEPTION_DOCUMENT_NOT_FOUND';
                    }
                }
            };
        }

    }

}());
