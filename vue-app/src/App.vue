<script setup lang="ts">

    import {reactive} from 'vue'
    import EditNum from './components/EditNum.vue'
    import FieldBox from './components/FieldBox.vue'
    import {ExternalConnect} from './External'

    const PROD_COLUMN = 0;
    const METRIC_COLUMN = 1;

    const ref:any = {data: null};
    let source = reactive(ref);
    ExternalConnect(response => { console.log('updating', response); ref.data = response.data });

</script>

<template>
    <input value="hi from Vue" />
    <div class="products-info" v-if="source?.data?.products">
        <article v-for="prod in source.data.products">
            <h2>{{ prod.name }}</h2>
            <EditNum name="Price" :value="prod.launch.price" />
            <p>
                {{ prod.description}}
            </p>
            <FieldBox name="Growth">
                <EditNum name="Cycle" :value="prod.growth.cycle" />
                <EditNum name="Min" :value="prod.growth.min" />
                <EditNum name="Max" :value="prod.growth.max" />
            </FieldBox>
            <FieldBox name="Launch">
                <EditNum name="Quarter" :value="prod.launch.qtr" />
                <EditNum name="Units" :value="prod.launch.units" />
            </FieldBox>
        </article>
    </div>
    <div style="clear:both"></div>
    <table class="data-points">
        <thead>
            <tr>
                <th v-for="label in source.data.headers">{{ label }}</th>
            </tr>
        </thead>
        <tr :class="'product-'+row[PROD_COLUMN]+' metric-'+row[METRIC_COLUMN]" v-for="row in source.data.rows">
            <td v-for="value in row">{{ value }}</td>
        </tr>
    </table>
</template>

<style scoped>
</style>
