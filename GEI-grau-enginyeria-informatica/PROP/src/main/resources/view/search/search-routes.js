(function () {
    'use strict';

    angular
        .module('project.search')
        .config(config);

    function config($stateProvider) {
        $stateProvider
            .state('project.search', {
                url: '/search',
                parent: 'project',
                abstract: true,
                views: {
                    'wrapper': {
                        templateUrl: 'search/search.tpl.html'
                    }
                }
            })
            .state('project.search.all', {
                url: '/all',
                parent: 'project.search',
                views: {
                    'search-content': {
                        templateUrl: 'search/all/search-all.tpl.html',
                        controller: 'SearchAllCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
            .state('project.search.author', {
                url: '/author',
                parent: 'project.search',
                views: {
                    'search-content': {
                        templateUrl: 'search/author/search-author.tpl.html',
                        controller: 'SearchAuthorCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
            .state('project.search.document', {
                url: '/document',
                parent: 'project.search',
                views: {
                    'search-content': {
                        templateUrl: 'search/document/search-document.tpl.html',
                        controller: 'SearchDocumentCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
            .state('project.search.boolean', {
                url: '/boolean',
                parent: 'project.search',
                views: {
                    'search-content': {
                        templateUrl: 'search/boolean/search-boolean.tpl.html',
                        controller: 'SearchBooleanCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
            .state('project.search.query', {
                url: '/query',
                parent: 'project.search',
                views: {
                    'search-content': {
                        templateUrl: 'search/query/search-query.tpl.html',
                        controller: 'SearchQueryCtrl',
                        controllerAs: 'vm'
                    }
                }
            })
    }
}());

