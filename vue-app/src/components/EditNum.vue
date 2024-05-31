<script setup>
    defineProps(['name', 'value'])
</script>

<template>
    <label class="edit-num">{{name}}<input :value="value" /></label>
</template>