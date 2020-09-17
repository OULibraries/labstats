<?php

class labstats_stats_handler_filter_id extends views_handler_filter_string {
    public function query() {
        // $this->value is not empty when the above form has been filled out.
        if (empty($this->value)) {
            return;
        }
        $this->ensure_my_table();
    }
}