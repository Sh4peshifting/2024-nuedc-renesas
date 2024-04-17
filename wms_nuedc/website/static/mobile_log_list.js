$(document).ready(function () {

    $(function updateTable() {
        $.ajax({
            url: '/repository/get_log_info/', type: 'POST', success: function (receivedData) {
                const source = `
         <md-list style="border-radius: 20px;">
                    <md-list-item>
                        <h5>日志</h5>
                    </md-list-item>
                    <md-divider></md-divider>
                    {{#each log_list}}
                    <md-list-item>
                        <div slot="headline">{{this.people}}</div>
                        <div slot="supporting-text">{{this.operation}}  {{this.other}}
                        </div>
                        <div slot="trailing-supporting-text">{{this.time}}</div>
                    </md-list-item>
                    {{/each}}
                </md-list>`;

                const template = Handlebars.compile(source);

                const html = template(receivedData);
                $(".log-list-box").html(html);
            }
        });
    });

});