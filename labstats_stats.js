/**
 * Created by smit0015 on 4/16/2017.
 */

!function ($) {

/**
 * The bento search question mark modals
 *
 * @type {{attach: Drupal.behaviors.oulib_bento.attach}}
 */
Drupal.behaviors.oulib_bento = {
    attach: function (context, settings) {

        var modal;
        var section;
        var mapID;

        $(".glyph-modal", context).click(function (event) {
            event.preventDefault();

            // Get the modal
            modal = document.getElementById(this.id + "-modal");

            section = $(this).data("id");

            var section_name = section;

            switch(section) {
                case "Architecture":
                    mapID = 1049;
                    break;
                case "Learning":
                    mapID = 1050;
                    section_name = "Learning Lab";
                    break;
                case "EIC":
                    mapID = 1051;
                    break;
                case "Engineering":
                    mapID = 1052;
                    break;
                case "Fine":
                    mapID = 1053;
                    section_name = "Fine Arts";
                    break;
                case "Fine Arts Library":
                    mapID = 1053;
                    break;
                    section_name = "Fine Arts";
                case "Geology":
                    mapID = 1054;
                    break;
                case "HCLC":
                    mapID = 1052;
                    break;
                default:
                    mapID = 1053;
            }

            // When the user clicks on the button, open the modal
            modal.style.display = "block";
            // Get the authorization ID from the config settings in drupal
            var authID = Drupal.settings.labstats_stats.authID;

            $("#mapTarget").LabMap({
                mapId: mapID,
                authId: authID,
                domain: "https://labstats.ou.edu",
                update: false,
                drawn: false
            });

            $(".modal_header_text").text('Computer Map for '+section_name);

            setTimeout(function(){
                var body_width = parseInt($('.modal-content').width());
                $('.modal-header').css('width', body_width);
                //$('.modal_header_text').css('width', body_width);
            },1000);
        });

        // Click the ok button to close the modal
        $(".search-modal-ok", context).click(function (event) {
            event.preventDefault();
            modal.style.display = "none";
        });

        // click the x to close the modal
        $(".close-modal", context).click(function (event) {
            event.preventDefault();

            modal.style.display = "none";
        });

        // When the user clicks anywhere outside of the modal, close it
        window.onclick = function (event) {
            if (event.target === modal) {
                modal.style.display = "none";
            }
        };
    }
};

$(window).resize(function() {
    var body_width = $('.modal-content').width();

    if (body_width) {
        $('.modal-header').css('width', body_width);
    }
});
}(jQuery);
