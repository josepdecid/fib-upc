(function () {
    'use strict';

    /**
     * @ngdoc object
     * @name project.constant:MenuValues
     *
     * @description
     *
     */
    angular
        .module('project')
        .value('menuItems', [
            {
                name: 'MENU_HOME',
                state: 'project.home',
                icon: 'home',
                selected: true
            },
            {
                name: 'MENU_SEARCH',
                state: 'project.search',
                icon: 'search',
                selected: false,
                collapsed: true,
                children: [
                    {
                        name: 'MENU_SEARCH_ALL',
                        state: 'project.search.all',
                        icon: 'list-alt',
                        selected: false
                    },
                    {
                        name: 'MENU_SEARCH_AUTHOR',
                        state: 'project.search.author',
                        icon: 'user',
                        selected: false
                    },
                    {
                        name: 'MENU_SEARCH_SINGLE_DOCUMENT',
                        state: 'project.search.document',
                        icon: 'file-text',
                        selected: false
                    },
                    {
                        name: 'MENU_SEARCH_BOOLEAN',
                        state: 'project.search.boolean',
                        icon: 'sitemap',
                        selected: false
                    },
                    {
                        name: 'MENU_SEARCH_QUERY',
                        state: 'project.search.query',
                        icon: 'question',
                        selected: false
                    }
                ]
            },
            {
                name: 'MENU_MANAGEMENT',
                state: 'project.manage.all',
                icon: 'pie-chart',
                selected: false,
                collapsed: true,
                children: [
                    {
                        name: 'MENU_MANAGEMENT_ALL',
                        state: 'project.manage.all',
                        icon: 'list-alt',
                        selected: false
                    },
                    {
                        name: 'MENU_MANAGEMENT_FAVOURITES',
                        state: 'project.manage.favourites',
                        icon: 'heart',
                        selected: false
                    }
                ]
            },
            {
                name: 'MENU_SETTINGS',
                state: 'project.settings',
                icon: 'gears',
                selected: false
            },
            {
                name: 'MENU_ABOUT',
                state: 'project.about',
                icon: 'question',
                selected: false
            }
        ]);
}());