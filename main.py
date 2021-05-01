import logging
import discord
import subprocess
from lib import process_output
from discord.ext import commands


class msg(commands.Cog):

    def __init__(self, bot):
        self.bot = bot
        self.logger = logging.getLogger(__name__)

    @commands.command(prefix="bb")
    async def buildbasic(self, ctx):
        msg = "BUILD FROM BASIC LANG IN C++"
        m: discord.Message = await ctx.send(msg)
        p = subprocess.Popen(["make"],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        _ = await process_output(p, m, msg, ctx)
        await ctx.send("ENDED.")

    @commands.command(prefix="db")
    async def debugbasic(self, ctx):
        msg = "DEBUG FROM BASIC LANG IN C++"
        m: discord.Message = await ctx.send(msg)
        p = subprocess.Popen(["make","-C","./plugin/BASIC_lang/"],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        _ = await process_output(p, m, msg, ctx)
        await ctx.send("ENDED.")
        msg = "chmod a+x ./basic"
        m: discord.Message = await ctx.send(msg)
        p = subprocess.Popen(["chmod","a+x","./plugin/BASIC_lang/basic"],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        _ = await process_output(p, m, msg, ctx)
        await ctx.send("ENDED.")
        msg = "RUN DEBUG"
        m: discord.Message = await ctx.send(msg)
        p = subprocess.Popen(["./plugin/BASIC_lang/basic"],
                             stdout=subprocess.PIPE,
                             stderr=subprocess.STDOUT)
        _ = await process_output(p, m, msg, ctx)
        await ctx.send("ENDED.")


def setup(bot):
    bot.add_cog(msg(bot))