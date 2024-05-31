<script setup>
    defineProps(['name'])
</script>

<template>
    <div class="field-box">
        <span class="label">{{name}}</span>
        <slot />
    </div>
</template>