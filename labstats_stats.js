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

            switch(section) {
                case "Architecture":
                    mapID = 1049;
                    break;
                case "Bizzell":
                    mapID = 1050;
                    break;
                case "EIC":
                    mapID = 1051;
                    break;
                case "Engineering":
                    mapID = 1052;
                    break;
                case "Fine Arts":
                    mapID = 1053;
                    break;
                case "Fine Arts Library":
                    mapID = 1053;
                    break;
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
            console.log(mapID);
             $("#mapTarget").LabMap({
                    mapId: mapID,
                    authId: authID,
                    domain: "https://labstats.ou.edu"
                });
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


}(jQuery);