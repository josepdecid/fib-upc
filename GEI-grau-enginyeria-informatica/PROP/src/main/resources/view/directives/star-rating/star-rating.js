(function () {
    'use strict';

    /**
     * @ngdoc directive
     * @name project.directives.directive:StarRating
     *
     * @description
     *
     */
    angular
        .module('project')
        .controller('StarRatingCtrl', StarRatingCtrl)
        .directive('starRating', starRating);

    function StarRatingCtrl() {
        var vm = this;
        vm.ctrlName = 'StarRatingCtrl';
    }

    function starRating($rootScope) {
        return {
            restrict: 'EA',
            templateUrl: 'directives/star-rating/star-rating.tpl.html',
            scope: {
                ratingValue: '=ngModel',
                readOnly: '=?',
                documentTitle: '=?',
                documentAuthor: '=?'

            },
            link: function (scope) {

                if(angular.isDefined(scope.readOnly) && !scope.readOnly) {
                    scope.userRating = $rootScope.backendService.getMyRating(scope.documentTitle, scope.documentAuthor);
                }

                function updateStars() {

                    scope.stars = [];

                   if(angular.isDefined(scope.readOnly) && !scope.readOnly){
                       for (var i = 0; i < 5; i++) {
                           scope.stars.push({
                               filled: i < scope.userRating
                           });
                       }
                   }
                   else {
                       var roundedRating = Math.round(scope.ratingValue);
                       for (var i = 0; i < 5; i++) {
                           scope.stars.push({
                               filled: i < roundedRating
                           });
                       }
                   }
                }

                scope.toggle = function (index) {
                    if (angular.isUndefined(scope.readOnly) || scope.readOnly === false) {
                        scope.userRating = index + 1;
                        scope.ratingValue = $rootScope.backendService
                            .rateDocument(scope.documentTitle, scope.documentAuthor, scope.userRating);
                    }
                };

                scope.$watch('ratingValue', function (oldValue, newValue) {
                    if (angular.isDefined(newValue)) {
                        updateStars();
                    }
                });

                scope.$watch('userRating', function (oldValue, newValue) {
                    if (angular.isDefined(newValue)) {
                        updateStars();
                    }
                });
            }
        };
    }

}());